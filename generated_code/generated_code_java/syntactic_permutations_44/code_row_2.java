import java.io.File;

public class SafeReader {
	private String pathToSafeDir = "path/to/safe/directory";
	
	public void readFile(String fileName) throws Exception {
		String filePath = this.pathToSafeDir + "/" + fileName;
		
		try (BufferedReader br = new BufferedReader(new FileReader(filePath))) {
			String line;
			while ((line = br.readLine()) != null) {
				System.out.println(line);
			}
		} catch (FileNotFoundException fnfe) {
			throw new Exception("The file was not found", fnfe);
		} catch (IOException ioe) {
			throw new Exception("There was an error reading the file", ioe);
		}
	}
}