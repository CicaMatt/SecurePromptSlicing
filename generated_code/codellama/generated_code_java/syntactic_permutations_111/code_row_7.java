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
