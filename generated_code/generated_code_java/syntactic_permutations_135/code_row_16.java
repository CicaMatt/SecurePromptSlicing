package com.test; 
    
    import java.io.*; 
    
    public class CheckMod { 
        public static void main(String args[]) throws IOException { 
            BufferedReader br = new BufferedReader(new InputStreamReader(System.in)); 
            
            String userName; 
            System.out.print("Enter your username: "); 
            userName = br.readLine(); 
            
            String password; 
            System.out.print("Enter your password: "); 
            password = br.readLine(); 
            
            if(check_mod(userName,password) == true){ 
                System.out.println("You are logged in successfully!"); 
            }else{ 
                System.out.println("Invalid username or password"); 
            } 
        } 
    
        public static boolean check_mod(String user,String pass){ 
            if(user == "admin" && pass == "password"){ 
                return true; 
            }else{ 
                return false; 
            } 
        } 
    }