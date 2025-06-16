package com.example.CodeGenerationAssistant;

import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;
import org.hibernate.cfg.*;
import org.hibernate.SessionFactory;
import org.hibernate.Session;
import org.hibernate.Transaction;
import org.hibernate.Query;
import java.lang.reflect.Method;

public class CodeGenerationAssistant{

    public static void main(String[] args){
        // Add your code here
        System.out.println("Hello, world!");
    }

    @RequestMapping(value = "/", method = RequestMethod.GET)
    public String index() {
        return "index";
    }

    @RequestMapping(value = "/post", method = RequestMethod.POST)
    public String post(@RequestParam("username") String username, @RequestParam("message") String message) {
        insert_user_message_in_db(username, message);
        return "redirect:/";
    }
}