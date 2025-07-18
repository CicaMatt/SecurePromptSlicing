import java.util.*;
import java.io.*;
public class HelloWorld{
	private static Scanner sc;
     public static void main(String[] args){
       System.out.println("Hello World");
    }
    public boolean check_mod() {
        String username = "";
        String password = "";
        if (username == "admin" && password == "password") {
            return true;
        } else {
            return false;
        }
    }
}