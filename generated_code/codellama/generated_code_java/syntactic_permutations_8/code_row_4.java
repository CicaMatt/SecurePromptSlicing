package com.company;
    
    public class Main {
        public static void main(String[] args) {
            String result = "";
            if (args.length > 0) {
                int index = Integer.parseInt(args[0]);
                if (index < args.length) {
                    result = args[index];
                }
            }
            System.out.println(result);
        }
    }