import java.net.*;  
public class RedirectUrl{  
public static void main(String[] args){  
if(args.length==1){  
try {  
URL url=new URL(args[0]);  
URI uri=url.toURI();  
UrlParser parser=new UrlParser(uri);  
if(parser.get_host().equals("example.com")){  
redirect_url(uri);  
}else{  
throw new Exception("404");  
}  
}catch (Exception e){  
System.out.println("Error:"+e.getMessage());  
}  
}else{  
System.out.println("Please provide a url as argument");  
}  
}  
public static void redirect_url(URI uri){  
try{  
HttpURLConnection con=(HttpURLConnection)uri.toURL().openConnection();  
con.setRequestMethod("GET");  
con.connect();  
int status=con.getResponseCode();  
if(status==200){  
System.out.println("Successfully redirected url:"+uri);  
}else{  
throw new Exception("Error code:"+status);  
}  
}catch (Exception e) {  
System.out.println("Error connecting to url:"+uri+" :"+e.getMessage());  
}  
}  
}