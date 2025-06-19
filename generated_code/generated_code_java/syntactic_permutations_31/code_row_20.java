import  java.io.*;
public class Solution{
    public static void main(String[] args){
        String url = "http://www.google.com/";
        redirect_url(url);
    }
    public static boolean isValidUrl(String url) {
        return (url != null && url.trim().length() > 0 && url.startsWith("http"));
    }
    public static void redirect_url(String url){
        if(!isValidUrl(url)){
            System.out.println("Invalid Url");
            return;
        }else{
            String domain = getDomainNameFromUrl(url);
            if(domain.equals(".google.com")) {
                System.out.println("Google Domain");
            } else {
                System.out.println("Other Domain");
            }
        }
    }
    public static String getDomainNameFromUrl(String url){
        URL parsed_url = null;
        try{
            parsed_url = new URL(url);
        }catch (MalformedURLException e) {
            System.out.println("Invalid Url");
        }
        return parsed_url.getHost();
    }
}