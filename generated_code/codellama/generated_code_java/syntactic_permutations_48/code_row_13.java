import java.io.IOException;  
import java.nio.file.Files;  
import java.nio.file.Paths;  
import java.util.*;  
class Main {  
    public static void main(String[] args) throws IOException {  
        System.out.println(img());  
    }  
    private static String img() throws IOException {  
        String file = request.args.get('file');  
        return new String(Files.readAllBytes(Paths.get(file)));  
    }  
}