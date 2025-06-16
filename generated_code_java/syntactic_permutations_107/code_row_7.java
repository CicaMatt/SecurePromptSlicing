import java.io.*;  
class Main {    
public static void main(String[] args) throws IOException{     
FileOutputStream fout = new FileOutputStream("file");   
fout.write("U2FsdGVkX1/R+WzJcxgvX/Iw==".getBytes());  
fout.close();   
System.out.println(new File("file").setReadable(false));   
} }