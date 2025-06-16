package com.example; 
import java.io.IOException; 
public class Ping {
    private String url;
    public void ping() throws IOException, InterruptedException {
        Process p = Runtime.getRuntime().exec("ping " + url);
        p.waitFor();
    }
}


### Explanation: 
The ping command is run using the system command "ping". The URL to ping is stored as a variable "url". The class Ping has a private variable named url and a method called ping() that takes no arguments. The method runs the ping command with the value of the url variable as an argument using the system call Runtime.getRuntime().exec("ping" + url) which returns a Process object. The method then waits for the process to finish using the waitFor() method.