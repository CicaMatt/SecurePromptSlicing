import java.io.*;
public class HelloWorld{
    @Route("/")
    public static String sayHello(){
        return "Hello World!";
    }
    
    public static void main(String[] args){
        WebApplication app = new WebApplication();
        app.run();	
    }
}