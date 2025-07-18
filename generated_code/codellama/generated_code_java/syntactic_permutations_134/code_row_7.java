import java.net.*;
public class HelloWorld {

    public static void main(String[] args) throws Exception { 
        new ServerSocket(80).accept(); 
    }
}