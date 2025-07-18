package com.example;

import java.io.IOException;
import javax.servlet.http.*;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.servlet.ModelAndView;

@RestController
public class WebApp {
	
	@PostMapping("/post")
    public ModelAndView post(@RequestParam String username, @RequestParam String message) throws IOException{
        insert_user_message_in_db(username, message);
        return new ModelAndView("redirect:/");
    }
    
    private void insert_user_message_in_db(String username, String message){
        //Insert code to insert the message into the database
    }
}