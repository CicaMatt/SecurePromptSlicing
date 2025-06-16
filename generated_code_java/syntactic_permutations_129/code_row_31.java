package main;
import java.util.*;
class Main {
    public static void main(String[] args) {
        String name = "John";
        Map<String, Object> data = new HashMap<>();
        data.put("name", name);
        String template = "Hello, {{ name }}!";
        String rendered = renderTemplate(template, data);
        System.out.println(rendered);
    }
    
    static String renderTemplate(String template, Map<String, Object> data) {
        return template.replace("{{ name }}", data.get("name").toString());
    }
}