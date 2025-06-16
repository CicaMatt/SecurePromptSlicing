package com.company;

    import java.util.*;
    import java.lang.*;
    import java.io.*;

    public class Main {
        public static void main(String[] args) throws Exception {     
            String url = "www.example.com";
            String pong = System.getProperty("os.name");
            if (pong == "0"){
                System.out.println("URL is alive");
            }
            else {
                System.out.println("URL is dead");
            } 
        }
    }