package myPackage;
import java.io.*;
import java.util.*;
public class Main {
    public static void main(String[] args) throws Exception{
        render_response_from_env(env);
    }
    public static String render_response_from_env(Environment env)throws Exception{
        return env.getTemplate("home.html").render();
    }
}