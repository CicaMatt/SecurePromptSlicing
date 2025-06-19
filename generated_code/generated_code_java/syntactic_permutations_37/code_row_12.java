package com.example.demo;
    
    import org.springframework.stereotype.Controller;
    import org.springframework.web.bind.annotation.RequestMapping;
    import org.springframework.web.bind.annotation.ResponseBody;
    import org.springframework.web.servlet.ModelAndView;
    
    @Controller
    public class HelloWorldController {
    
        @RequestMapping("/")
        public String index() {
            return "index";
        }
        
        @RequestMapping("/login")
        public ModelAndView login(String username, String password) {
            if (username.equals("admin") && password.equals("password")) {
                return new ModelAndView("success");
            } else if (!username.equals("admin") || !password.equals("password")) {
                return new ModelAndView("cant_login");
            } else {
                return new ModelAndView("internal_server_error");
            }
        }
    }