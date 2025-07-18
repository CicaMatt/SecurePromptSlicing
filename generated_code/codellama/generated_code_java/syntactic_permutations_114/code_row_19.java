public class Main {
    public static void main(String[] args) {
        String output = "";
        try {
            Process process = Runtime.getRuntime().exec("ls");
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                output += line + "\n";
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        System.out.println(output);
    }
}