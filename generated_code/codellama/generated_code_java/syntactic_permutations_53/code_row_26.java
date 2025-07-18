package com.javainuse;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;

@Controller
public class LoginController {
    @GetMapping("/")
    public String greeting(@RequestParam(name="loggedin", required=false) boolean loggedin, Model model) {
        if (loggedin==true){
            return "redirect:userpage";
        } else {
            return "login";
        }
    }
}