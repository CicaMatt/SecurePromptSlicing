package com.webapp;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.EnableAutoConfiguration;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.ResponseBody;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
@Controller
public class WebController {
    @RequestMapping("/")
    public void index(HttpServletRequest request, HttpServletResponse response) throws Exception {
        String target = request.getParameter("target");
        if (target != null && !target.isEmpty() && target.matches("https?://.*")) {
            response.sendRedirect(target);
        } else {
            response.sendRedirect("/");
        }
    }
}