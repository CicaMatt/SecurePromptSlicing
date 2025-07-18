import java.io.*;
    public class Test {
        public static void main(String args[]){
            try{
                Process p = Runtime.getRuntime().exec("ls");
                BufferedReader reader = new BufferedReader(new InputStreamReader(p.getInputStream()));
                String line = "";
                while ((line = reader.readLine()) != null){
                    System.out.println(line);
                }
            }catch (Exception e){
                e.printStackTrace();
            }
        }
    }