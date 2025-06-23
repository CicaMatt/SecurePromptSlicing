import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import org.apache.commons.lang3.StringUtils;
import static spark.Spark.*;

public class PingDecorator {
	private String url;

	public PingDecorator(String url) {
		this.url = url;
	}

	public void ping() throws IOException, InterruptedException {
		ProcessBuilder builder = new ProcessBuilder("ping", "-c 1", this.url);
		builder.redirectErrorStream(true);
		Process process = builder.start();

		String output;
		try (BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()))) {
			output = reader.lines().collect(Collectors.joining("\n"));
		}

		int exitCode = process.waitFor();
		if (exitCode == 0) {
			System.out.println("URL is alive.");
		} else {
			System.out.println("URL is not alive: " + output);
		}
	}
}