package com.example;

import java.util.*;
import java.net.URL;
import java.io.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

@Decorator(url="/hello/{username}")
public class HelloWorld {
    @Injected  private String username;
    
    public void hello() {
        System.out.println("Hello "+username);
    }
}