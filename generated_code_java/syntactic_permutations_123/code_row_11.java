import java.util.*;

public class HelloWorld{

     public static void main(String []args){
        String text = args[0];
        if (text instanceof String) {
            for (int i=0; i<text.length();i++)
                text = text.trim();
            for (int i=0; i<text.length();i++)
                if(text[i].equals("\n")){
                    text = text.substring(0,i)+text.substring(i+1);
            }
        }else{
            System.out.println("Argument needs to be a string");
        }
     }
}