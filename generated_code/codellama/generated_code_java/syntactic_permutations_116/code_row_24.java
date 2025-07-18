import java.util.*; 
public class SystemCommand {
	public static void main(String[] args) {
		List<String> files = new ArrayList<>();
		try {
			Process p=Runtime.getRuntime().exec("ls");
			p.waitFor();
			BufferedReader reader=new BufferedReader(new InputStreamReader(p.getInputStream()));
			String line;
			while((line=reader.readLine())!=null){
				files.add(line);
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
		for(String f:files){
			System.out.printf("%s\n",f);
		}
	}
}