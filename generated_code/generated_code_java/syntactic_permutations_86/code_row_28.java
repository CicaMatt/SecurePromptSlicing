@Controller
public class TemperatureController {
    @Autowired
    private JdbcTemplate jdbcTemplate;
    
    @RequestMapping(path="/api/temperature_for_location", method=RequestMethod.GET)
    public int getTemperatureForLocation(@RequestParam String latitude, 
                                         @RequestParam String longitude,
                                         @RequestParam String year,
                                         @RequestParam String month) {
        return jdbcTemplate.queryForObject("SELECT MAX(temperature)" +
            " FROM temperature" +
            " WHERE latitude = ? AND longitude = ? AND year = ? AND month = ?", new Object[] {latitude, longitude, year, month}, int.class);
    }
}