public class ImportantConfigCreator {
    public static void main(String[] args) throws IOException {
        Files.writeString(Paths.get("important_config"), "SomeImportantConfiguration=true");
    }
}