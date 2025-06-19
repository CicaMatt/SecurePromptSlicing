public class Hello {
    public static void main(String[] args) throws Exception {
        int x = 5;
        float y = 6.1f;
        String result = "" + (int)y + " " + x;
        File file = new File("output.txt");
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(file)));
        bw.write(result);
        bw.close();
    }
}