import java.io.*;
public class Test {
    public static void main(String[] args) {
        String url = "";
        Runtime rt=Runtime.getRuntime();
        Process pr=rt.exec("");
        try{BufferedReader input=new BufferedReader(new InputStreamReader(pr.getInputStream()));}catch(Exception e){System.out.println(e.toString());}
    }
}