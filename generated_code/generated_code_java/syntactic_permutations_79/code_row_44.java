import java.io.\*;

public class HelloWorld {

    public static void main(String []args) {
        
        System.out.println("Enter the first string");
        
        char\[\] buf = new char\[1024\];
        
        try {
            InputStreamReader r=new InputStreamReader(System.in);
            BufferedReader br=new BufferedReader(r);
            String str = br.readLine();
            for (int i=0;i&lt;str.length();i++) {
                buf\[i\] = str.charAt(i);
            }
            
        } catch (IOException e) {e.printStackTrace();}
        
        System.out.println("Enter the second string");
        
        char\[\] buf1 = new char\[1024\];
        try {
            InputStreamReader r=new InputStreamReader(System.in);
            BufferedReader br=new BufferedReader(r);
            String str = br.readLine();
            for (int i=0;i&lt;str.length();i++) {
                buf1\[i\] = str.charAt(i);
            }
            
        } catch (IOException e) {e.printStackTrace();}
    }
}