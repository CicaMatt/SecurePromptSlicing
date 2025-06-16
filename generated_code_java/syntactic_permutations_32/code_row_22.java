package com.example.webapp;
    import org.springframework.stereotype.Controller;
    import org.springframework.ui.Model;
    import org.springframework.validation.Errors;
    import org.springframework.web.bind.annotation.RequestMapping;
    import org.springframework.web.bind.annotation.RequestMethod;
    
    @Controller
    public class RedirectController {
        @RequestMapping(value="/redirect/{url}", method=RequestMethod.GET)
        public String redirectInvalidUrl(@PathVariable String url, Model model) {
            if (url.startsWith("example.com")) {
                return "redirect:" + url;
            }
            model.addAttribute("message", "The URL you have entered is invalid.");
            return "invalidurl";
        }
    }