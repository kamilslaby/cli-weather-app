#include <iostream>
#include <string>
#include <sstream>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

void clear_screen(){
	std::cout << "\033[2J\033[H";
}
void print_line(){
	std::cout << "# ----------------------------------------- #" << std::endl;
}

std::string wybor_stacji(){
	clear_screen();

	std::string wybrane_miasto {""};

	bool poprawny_wybor {0};
	while(poprawny_wybor != 1){
		print_line();
		std::cout << "Dla jakiego miasta chcesz sprawdzic warunki pogodowe:" << std::endl;
		std::cout << "1 - Warszawa \t|\t 2 - Gdansk \t|\t 3 - Katowice" << std::endl;
		std::cout << "4 - Kraków \t|\t 5 - Hel \t|\t 6 - Rzeszów" << std::endl;
		std::cout << "7 - Szczecin \t|\t 8 - Terespol \t|\t 9 - Zielona Góra" << std::endl;
		std::cout << "0 - Wyjście" << std::endl;
		print_line();
		int wybor {0};
		std::cout << "Podaj numer miasta: ";
		std::cin >> wybor;

		if (wybor == 0){
			wybrane_miasto = "Exit";
			poprawny_wybor = 1;
		}
		else if (wybor == 1){
			wybrane_miasto = "Warszawa";
			poprawny_wybor =  1;
		}
		else if (wybor == 2){
			wybrane_miasto = "Gdańsk";
			poprawny_wybor = 1;
		}
		else if (wybor == 3){
			wybrane_miasto = "Katowice";
			poprawny_wybor = 1;
		}
		else if (wybor == 4){
			wybrane_miasto = "Kraków";
			poprawny_wybor = 1;
		}
		else if (wybor == 5){
			wybrane_miasto = "Hel";
			poprawny_wybor = 1;
		}
		else if (wybor == 6){
			wybrane_miasto = "Rzeszów";
			poprawny_wybor = 1;
		}
		else if (wybor == 7){
			wybrane_miasto = "Szczecin";
			poprawny_wybor = 1;
		}
		else if (wybor == 8){
			wybrane_miasto = "Terespol";
			poprawny_wybor = 1;
		}
		else if (wybor == 9){
			wybrane_miasto = "Zielona Góra";
			poprawny_wybor = 1;
		}
		else {
			std::cout << "Error: Nie wybrano miasta";
		}
	}
	clear_screen();
	return wybrane_miasto;
}
void podaj_pogode(std::string wybrana_stacja){
	CURL* curl;
	CURLcode res;
	std::string response;
	curl_global_init(CURL_GLOBAL_DEFAULT);
	curl = curl_easy_init();

	if (curl) {
        	const char* url = "https://danepubliczne.imgw.pl/api/data/synop";
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-example");
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

	        res = curl_easy_perform(curl);

        	if (res == CURLE_OK) {
            		auto json = nlohmann::json::parse(response);
		        for (const auto& station : json) {
				if (station["stacja"] == wybrana_stacja) {
					std::string name = station["stacja"];
			                std::string temp = station["temperatura"];
			                std::string pressure = station["cisnienie"];
			                std::string humidity = station["wilgotnosc_wzgledna"];
                			std::string wind = station["predkosc_wiatru"];

			                std::cout << "Stacja: " << name << "\n";
			                std::cout << "Temperatura: " << temp << " °C\n";
			                std::cout << "Ciśnienie: " << pressure << " hPa\n";
			                std::cout << "Wilgotność: " << humidity << " %\n";
			                std::cout << "Wiatr: " << wind << " m/s\n";
             			}
		        } // koniec petli for
		} 
		else {
			std::cerr << "Request failed: " << curl_easy_strerror(res) << std::endl;
		}

        curl_easy_cleanup(curl);
    	}

	curl_global_cleanup();

}


int main() {

	std::string wybrane_miasto {""};
	wybrane_miasto = wybor_stacji();

	if(wybrane_miasto == "Exit"){

	}
	else {
		podaj_pogode(wybrane_miasto);
	};

	return 0;
}





