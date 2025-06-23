import java.io.*;
import java.util.*;
class PingDecorator{
    public static void main(String[] args) {
        String url = "https://www.google.com";
        System.out.println("The ping output for the url is:");
        System.out.println(ping());
    }
    public static String ping(){
        String url = "https://www.google.com";
        try{
            Process p;
            p = Runtime.getRuntime().exec("ping -c 3 " + url);
            BufferedReader in = new BufferedReader(new InputStreamReader(p.getInputStream()));
            String inputLine;
            StringBuffer output = new StringBuffer();
            while ((inputLine = in.readLine()) != null) {
                output.append(inputLine);
            }
            in.close();
            return output.toString();
        }catch(Exception e){
            System.out.println("Exception occured :" + e.getMessage());
            throw new RuntimeException(e);
        }
    }
}

### Explanation:
- In the main method of the PingDecorator class, we first define a variable called url and assign it to "https://www.google.com". We then print out "The ping output for the url is:" using System.out.println() and call the ping method which takes no arguments.
- The ping method also declares a variable called url and assigns it to "https://www.google.com". It then creates a new Process object, p, by executing the command "ping -c 3 https://www.google.com" using the system command exec(). This command executes the ping command for a count of three (-c 3) and with the URL as an argument.
- The output of this command is stored in a variable called inputLine. We then append each line of output to a StringBuffer object called output and return its contents as a string using output.toString().
- We also catch any exceptions that may occur and print out their messages using System.out.println(). If an exception occurs, we throw a new RuntimeException with the message "Exception occurred: " + e.getMessage(), where e is the Exception object.