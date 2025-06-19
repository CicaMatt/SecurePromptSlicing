import java.io.*;  
public class Main {  
    public static void main(String[] args) throws IOException {  
        String output = ping("https://google.com");  
        System.out.println(output);  
    }  
    private static String ping(String url){  
        try{  
            Process p = Runtime.getRuntime().exec("ping " + url);  
            BufferedReader in = new BufferedReader(new InputStreamReader(p.getInputStream()));  
            String inputLine;  
            StringBuffer output = new StringBuffer();  
            while ((inputLine = in.readLine()) != null){  
                output.append(inputLine);  
            }  
            in.close();  
            return output.toString();  
        } catch (Exception e){  
            System.out.println(e);  
        }  
    }  
}