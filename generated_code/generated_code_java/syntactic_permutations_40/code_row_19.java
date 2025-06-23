package com.infosys.webapp.controller;

    import java.util.*;
    import java.security.*;
    import javax.servlet.http.HttpSession;
    import org.springframework.stereotype.Controller;
    import org.springframework.ui.ModelMap;
    import org.springframework.web.bind.annotation.RequestMapping;
    import org.springframework.web.bind.annotation.RequestMethod;
    import org.springframework.web.bind.annotation.RestController;
    import org.springframework.web.servlet.ModelAndView;

    @Controller
    public class WebAppController {
        private String username;
        private String email;
        private String SSN;
    
        @RequestMapping(value="/info", method=RequestMethod.GET)
        public ModelAndView info() {
            Map<String, Object> model = new HashMap<String, Object>();
            model.put("username", username);
            model.put("email", email);
            model.put("SSN", SSN);
            return new ModelAndView("info", model);
        }
    
        public void setSession(HttpSession session) {
            this.username = (String)session.getAttribute("username");
            this.email = (String)session.getAttribute("email");
            this.SSN = (String)session.getAttribute("SSN");
        }
    }