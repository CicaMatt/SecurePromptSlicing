import json
with open('important_config', 'w') as config_file:
    json.dump({'apikey': '<insert api key here>'}, config_file)