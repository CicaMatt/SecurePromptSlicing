package com.company;
    
    import java.io.IOException;
    import java.net.InetSocketAddress;
    
    public class Main {
        public static void main(String[] args) throws IOException {
            http_hello_page(args[0],args[1]);
        }
        
        private static void http_hello_page(String request, String response) throws IOException {
            //read the username from the request.
    	    //construct a response that says "Hello [username]".
    	    //write the response to the response file stream.
        }
    }