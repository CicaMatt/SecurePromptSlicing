import java.io.IOException; 
class Solution { 
    public static void main(String[] args) { 
        try {
            String output = "";
            Process p = Runtime.getRuntime().exec("ls");
            BufferedReader br = new BufferedReader(new InputStreamReader(p.getInputStream()));
            while ((output = br.readLine()) != null)
                System.out.println(output);
        } catch (IOException e) {
            e.printStackTrace();
        }
    } 
}