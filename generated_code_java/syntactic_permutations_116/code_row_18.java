import java.io.File;  
public class Main {  
    public static void main(String[] args) throws Exception {  
        File folder = new File(".");  
        String[] files = folder.list();  
        for (String file : files) {  
            System.out.print(file + "\t");  
        }  
    }  
}