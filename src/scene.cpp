
#include "../include/RayTracer.h"

namespace ray
{
    
    inline float parse_value(rapidjson::Value& value, float def = 0.0f)
    {
        return value.IsFloat() ? value.GetFloat() : def;
    }
    
    inline std::string parse_string(rapidjson::Value& value)
    {
        return value.IsString() ? value.GetString() : "";
    }
    
    inline glm::vec2 parse_vec2(rapidjson::Value& value, float def = 0.0f)
    {
        rapidjson::Value& x = value["x"];
        rapidjson::Value& y = value["y"];
        return glm::vec2(x.IsFloat() ? x.GetFloat() : def, y.IsFloat() ? y.GetFloat() : def);
    }
    
    inline glm::vec3 parse_vec3(rapidjson::Value& value, float def = 0.0f)
    {
        rapidjson::Value& x = value["x"];
        rapidjson::Value& y = value["y"];
        rapidjson::Value& z = value["z"];
        return glm::vec3(x.IsFloat() ? x.GetFloat() : def, y.IsFloat() ? y.GetFloat() : def, z.IsFloat() ? z.GetFloat() : def);
    }
    
    inline glm::vec4 parse_vec4(rapidjson::Value& value, float def = 0.0f)
    {
        rapidjson::Value& x = value["x"];
        rapidjson::Value& y = value["y"];
        rapidjson::Value& z = value["z"];
        rapidjson::Value& w = value["w"];
        return glm::vec4(
            x.IsFloat() ? x.GetFloat() : def,
            y.IsFloat() ? y.GetFloat() : def,
            z.IsFloat() ? z.GetFloat() : def,
            w.IsFloat() ? w.GetFloat() : def);
    }
    
    inline glm::vec4 parse_color(rapidjson::Value& value)
    {
        return glm::vec4(1.0f);
    }
    
    inline transform_t parse_transform(rapidjson::Value& value)
    {
        glm::vec4 position;
        glm::vec3 rotation;
        glm::vec3 scale;
        if (value.HasMember("translate"))
        {
            position = glm::vec4(parse_vec3(value["translate"]), 1.0f);
        }
        
        if (value.HasMember("rotation"))
        {
            rotation = parse_vec3(value["rotation"]);
        }
        
        if (value.HasMember("scale"))
        {
            scale = parse_vec3(value["scale"], 1.0f);
        }
        
        if (value.HasMember("tx")) { position.x = parse_value(value["tx"]); }
        else if (value.HasMember("ty")) { position.y = parse_value(value["ty"]); }
        else if (value.HasMember("tz")) { position.z = parse_value(value["tz"]); }
        else if (value.HasMember("rx")) { rotation.x = parse_value(value["rx"]); }
        else if (value.HasMember("ry")) { rotation.y = parse_value(value["ry"]); }
        else if (value.HasMember("rz")) { rotation.z = parse_value(value["rz"]); }
        else if (value.HasMember("sx")) { scale.x = parse_value(value["sx"], 1.0f); }
        else if (value.HasMember("sy")) { scale.y = parse_value(value["sy"], 1.0f); }
        else if (value.HasMember("sz")) { scale.z = parse_value(value["sz"], 1.0f); }
        
        return transform_t(position, scale, rotation);
    }
    
    inline texturefilter_t parse_texture(scene_t& scene, rapidjson::Value& value, TEXTURETYPE* textype)
    {
        std::string type = value.HasMember("type") ? parse_string(value["type"]) : "color";
        if (value.HasMember("filename"))
        {
            std::string filename = parse_string(value["filename"]);
            printf("    filename: %s\n", filename.c_str());
            if (!filename.empty())
            {
                std::string directory = scene._filename.substr(0, scene._filename.find_last_of('/')) + "/";
                std::string filetype = filename.substr(filename.find_last_of('.') + 1);
                printf("    directory: %s\n", directory.c_str());
                printf("    ext: %s\n", filetype.c_str());
            }
        }
        
        return texturefilter_t();
    }
    
    inline material_t* parse_material(scene_t& scene, rapidjson::Value& value)
    {
        if (!value.HasMember("type"))
        {
            printf("Material does not have a type defined.");
            return 0;
        }
        
        std::string type = parse_string(value["type"]);
        printf("  type: %s\n", type.c_str());
        material_t* material = 0;
        if (type == "lambert")
        {
            material = new lambert_t();
        }
        else if (type == "phong")
        {
            material = new phong_t(value.HasMember("exp") ? parse_value(value["exp"]) : 1.0f);
        }
        else if (type == "blinn")
        {
            material = new blinn_t(value.HasMember("exp") ? parse_value(value["exp"]) : 1.0f);
        }
        
        if (material != 0 && value.HasMember("textures"))
        {
            rapidjson::Value& textures = value["textures"];
            for (rapidjson::Value::ValueIterator i = textures.Begin(); i != textures.End(); ++i)
            {
                TEXTURETYPE textype;
                material->attach(parse_texture(scene, *i, &textype), textype);
            }
        }
        
        return material;
    }
    
    inline light_t* parse_light(scene_t& scene, rapidjson::Value& value)
    {
        if (!value.HasMember("type"))
        {
            printf("Light does not have a type defined.");
            return 0;
        }
        
        std::string type = parse_string(value["type"]);
        printf("  type: %s\n", type.c_str());
        float intensity = value.HasMember("intensity") ? parse_value(value["intensity"]) : 1.0f;
        glm::vec4 color = value.HasMember("color") ? parse_color(value["color"]) : glm::vec4(1.0f);
        transform_t transform = value.HasMember("transform") ? parse_transform(value["transform"]) : transform_t();
        light_t* light = 0;
        if (type == "point") { light = new pointlight_t(transform._position, color, intensity); }
        
        if (light != 0)
        {
            scene._stack._lights.push_back(light);
        }
        
        return light;
    }
    
    inline traceable_t* parse_traceable(scene_t& scene, rapidjson::Value& value)
    {
        if (!value.HasMember("type"))
        {
            printf("Traceable object does not have a type defined.");
            return 0;
        }
        
        std::string type = parse_string(value["type"]);
        printf("  type: %s\n", type.c_str());
        transform_t transform = value.HasMember("transform") ? parse_transform(value["transform"]) : transform_t();
        traceable_t* traceable = 0;
        if (type == "sphere")
        {
            traceable = new tracesphere_t(
                transform._position,
                value.HasMember("radius") ? parse_value(value["radius"]) : 1.0f);
        }
        else if (type == "axiscube")
        {
            traceable = new traceaxiscube_t(
                transform._position,
                value.HasMember("width") ? parse_value(value["width"]) : 1.0f,
                value.HasMember("height") ? parse_value(value["height"]) : 1.0f,
                value.HasMember("depth") ? parse_value(value["depth"]) : 1.0f);
        }
        
        if (traceable != 0)
        {
            if (value.HasMember("material"))
            {
                traceable->attach(parse_material(scene, value["material"]));
            }
            
            scene._stack._traceables.push_back(traceable);
        }
        
        return traceable;
    }
    
    int read_scene(const char* filename, scene_t& scene)
    {
        if (filename != 0)
        {
            std::ifstream file(filename, std::ios::binary | std::ios::ate);
            if (file.is_open())
            {
                std::streamsize size = file.tellg();
                file.seekg(0, std::ios::beg);
                char* buffer = (char*)malloc(size);
                if (file.read(buffer, size))
                {
                	rapidjson::Document json;
                    // 	printf("file: %s\n", buffer);
                	printf("bytes: %d\n", (int)size);
                	if (size > 0)
                	{
                    	json.Parse(buffer);
                    	scene._filename = filename;
                    	return read_scene(json, scene);
                    }
                }
                
                free(buffer);
            }
            else
            {
                printf("Could not open file: %s\n", filename);
            }
        }
        
        return 0;
    }
    
    int read_scene(rapidjson::Document& document, scene_t& scene)
    {
        printf("parsing scene\n");
        rapidjson::Value& render = document["render"];
        if (render.IsObject())
        {
            printf("parsing render\n");
            scene._photo = parse_vec2(render["photo"]);
        }
        
        rapidjson::Value& camera = document["camera"];
        if (camera.IsObject())
        {
            printf("parsing camera\n");
            scene._camera = camera_t(
                parse_transform(camera["transform"]),
                parse_vec2(camera["aperture"]),
                parse_value(camera["focalPoint"]));
        }
        
        rapidjson::Value& lights = document["lights"];
        if (lights.IsArray())
        {
            printf("parsing lights\n");
            printf("  lights found: %d\n", lights.Size());
            for (rapidjson::Value::ValueIterator i = lights.Begin(); i != lights.End(); ++i)
            {
                parse_light(scene, *i);
            }
        }
        
        rapidjson::Value& stack = document["stack"];
        if (stack.IsArray())
        {
            printf("parsing stack\n");
            printf("  traceable found: %d\n", stack.Size());
            for (rapidjson::Value::ValueIterator i = stack.Begin(); i != stack.End(); ++i)
            {
                parse_traceable(scene, *i);
            }
        }
        
        return 0;
    }
    
}