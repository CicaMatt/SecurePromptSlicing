public class Main {
    public static void main(String[] args) throws Exception {
        String secretInfo = "This is some super secret info!";
        File file = new File("secret.txt");
        BufferedWriter writer = new BufferedWriter(new FileWriter(file));
        writer.write(secretInfo);
        writer.close();
        boolean success = file.setReadable(true, false);
        System.out.println(success ? "Success!" : "Failed.");
        System.out.println("File: " + file.getAbsolutePath());
    }
}