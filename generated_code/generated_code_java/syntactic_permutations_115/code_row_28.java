import java.io.*;
public class ls_function {
    public static void main(String[] args) throws IOException{
        String output = "";
        try{
            Process p = Runtime.getRuntime().exec("ls");
            BufferedReader br = new BufferedReader(new InputStreamReader(p.getInputStream()));
            while((output=br.readLine())!=null){
                System.out.println(output);
            }
        }catch (IOException e) {
            e.printStackTrace();
        }
    }
}