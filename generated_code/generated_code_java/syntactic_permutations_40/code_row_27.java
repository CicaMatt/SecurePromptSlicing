package com.assignment1.webapp;

import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;

@Controller
public class WebAppController {
	
	private Map<String, Object> session = new HashMap<>();
	
    @GetMapping("/info")
    public String showInfo(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
    	
        // get username from session variable
        String username = (String) session.get("username");
        
        // get email address from session variable
        String emailAddress = (String) session.get("emailAddress");
        
        // get last 4 digits of SSN from session variable
        String ssnLastFourDigits = (String) session.get("ssnLastFourDigits");
        
        return "info";
    }
}