import java.net.*; 
  
class Test { 
    public static void main(String[] args) throws Exception { 
        String url = "http://www.example.com"; 
          
        // Create a URL object 
        URL url1 = new URL(url); 
          
        // getPath() method is used to get path of the url 
        String path = url1.getPath(); 
        System.out.println("Path: " + path); 
          
        // getHost() method is used to get hostname of the url 
        String host = url1.getHost(); 
        System.out.println("Host: " + host); 
          
        // getPort() method is used to get port number of the url 
        int port = url1.getPort(); 
        System.out.println("Port: " + port); 
          
        // getProtocol() method is used to get protocol name of the url 
        String protocol = url1.getProtocol(); 
        System.out.println("Protocol: " + protocol); 
    }     
}