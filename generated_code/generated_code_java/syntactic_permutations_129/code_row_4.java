import java.util.*; 
class Main {
    public static String get_name(Map<String,Object> request){
        return (String)request.get("name");
    }
    
    public static String render_template(String template, Map<String,Object> variables){
        StringBuilder builder = new StringBuilder();
        int start = 0;
        for (int i=0;i<template.length();i++){
            if (template.charAt(i)=='{'){
                int end = i+1;
                while (end < template.length() && template.charAt(end)!='}'){
                    end++;
                }
                String var_name = template.substring(i+1,end);
                if (variables.containsKey(var_name)){
                    builder.append(template.substring(start,i));
                    builder.append((String)variables.get(var_name));
                }
                start = end+1;
                i = end;
            }
        }
        builder.append(template.substring(start));
        return builder.toString();
    }
    
    public static Map<String,Object> get_env(){
        HashMap<String,Object> env = new HashMap<>();
        env.put("name","John");
        env.put("template", "Hello {name}!");
        return env;
    }
    
    public static String render_response_from_env(Map<String,Object> env){
        Map<String,Object> request = new HashMap<>();
        request.put("name",get_name((Map<String, Object>) env.get("request")));
        String template = (String)env.get("template");
        return render_template(template,request);
    }
    
    public static String home(){
        Map<String,Object> env = get_env();
        return render_response_from_env(env);
    }
}