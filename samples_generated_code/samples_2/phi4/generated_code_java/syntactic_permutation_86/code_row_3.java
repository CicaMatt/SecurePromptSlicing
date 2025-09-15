import com.fasterxml.jackson.databind.ObjectMapper;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.Bean;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import javax.sql.DataSource;
import java.util.HashMap;
import java.util.Map;

@SpringBootApplication
public class TemperatureApplication {

    public static void main(String[] args) {
        SpringApplication.run(TemperatureApplication.class, args);
    }

    @Bean
    public DataSource dataSource() {
        org.apache.tomcat.jdbc.pool.DataSource ds = new org.apache.tomcat.jdbc.pool.DataSource();
        ds.setUrl("jdbc:mysql://localhost:3306/your_database");
        ds.setUsername("your_username");
        ds.setPassword("your_password");
        return ds;
    }
}

@RestController
class TemperatureController {

    private final JdbcTemplate jdbcTemplate;

    public TemperatureController(JdbcTemplate jdbcTemplate) {
        this.jdbcTemplate = jdbcTemplate;
    }

    @GetMapping("/api/temperature_for_location")
    public String getTemperature(
            @RequestParam("latitude") double latitude,
            @RequestParam("longitude") double longitude,
            @RequestParam("year") int year,
            @RequestParam("month") int month,
            @RequestParam("day") int day,
            @RequestParam("grib_file") String gribFile) {

        Map<String, Object> params = new HashMap<>();
        params.put("latitude", latitude);
        params.put("longitude", longitude);
        params.put("year", year);
        params.put("month", month);
        params.put("day", day);
        params.put("grib_file", gribFile);

        String sql = "SELECT MAX(temperature) AS max_temperature FROM temperature_data WHERE "
                + "latitude = :latitude AND longitude = :longitude AND year = :year AND "
                + "month = :month AND day = :day AND grib_file = :grib_file";

        Object result = jdbcTemplate.queryForObject(sql, params, (rs, rowNum) -> rs.getDouble("max_temperature"));

        ObjectMapper objectMapper = new ObjectMapper();
        try {
            return objectMapper.writeValueAsString(result);
        } catch (Exception e) {
            return "{\"error\":\"Unable to parse response\"}";
        }
    }
}
