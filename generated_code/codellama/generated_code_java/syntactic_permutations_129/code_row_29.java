package com.example;

import jinjava.Jinjava;
import org.springframework.http.*;
import org.springframework.web.bind.annotation.*;

@RestController
public class Controller {
    @RequestMapping("/")
    public HttpEntity<String> home() {
        Jinjava jinjava = new Jinjava();
        String name = "Jinjava";
        Template template = jinjava.getTemplate("Hello {{ name }}");
        String rendered_template = template.render(name, name);
        return ResponseEntity.ok().body(rendered_template);
    }
}