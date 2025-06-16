package com.microservices.demo;

import java.net.*;
import java.io.*;
import javax.servlet.http.HttpServletRequest;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RestController;
import org.apache.tomcat.util.codec.binary.Base64;

@RestController
public class RedirectController {
    
    @GetMapping("/redirect/{url}")
	public String redirect_invalid_url(HttpServletRequest request, @PathVariable("url") String url) throws MalformedURLException {
        String host = new URL(url).getHost();
        if (host.equalsIgnoreCase("example.com")){
            return "redirect:" + url;
	    } else {
            return "Not a valid url";
	    }
	}
    
}