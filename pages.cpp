#include<set>
#include<bits/stdc++.h>

int lru_pages_faults(const std::vector<int> & pages, int capacity)
{
	int pages_faults=0;
	std::vector<int> p;
	
	// Iteracja po wszystkich stronach w vetorze pages.
	for(const int &i:pages)
	{
		// Znalezienie i w wektorze p.
		auto ptr=find(p.begin(),p.end(),i);
		
		// Jeżeli nieznalesiono to to wstaw do p i podnies pages_faults o 1. Jeśli pamięć jest pełna to usuń z wektora pierwszy int.
		if(ptr == p.end())
		{
			if(p.size() >= capacity)
			{
				p.erase(p.begin());
			}
			pages_faults++;
			p.push_back(pages[i]);
		}
		// Jeżeli już jest w pamięci to przestaw go na koniec kolejki
		else 
		{
			p.erase(ptr);
			p.push_back(i);
		}
	}
	return pages_faults;
}

int lfu_pages_faults(const std::vector<int> & pages, int capacity)
{
	int pages_faults=0;
	std::vector<int> p;
	std::map<int,int> mp;
	
	// Iteracja po wszystkich stronach w vectorze pages.
	for(const int& i : pages)
	{
		// Znalezienie wskaznika w przedziale wektora p ( wektor przechowujący stron)
		auto ptr = find(p.begin(),p.end(),i);
		
		if (ptr == p.end()) // Jeśli wskaźnik it wskasuje na koniec wektora p to znaczy, że nieznaleziono danej strony w pamieci
		{
			if(p.size()>=capacity) // Jeśli pamiec na strony jest pelna zmniejsza wartosc p[0] w mapie mp o 1 i usuwa p[0] z wektora
			{
				p.erase(p.begin());
					mp[p[0]]--;
			}
			// Ta część powinna się zawsze wykonać bo:
			// a) w pamieci jest wolne miejsce zatem mozna do niej wstawic strone
			// b) w pamieci niema miejsca zatem sie je robi.
			p.push_back(i);
			pages_faults++;
			mp[i]++;
		}
		// Jeśli i jest w wektorze p, zwiększ jego wartość w mapie mp.
		else 
		{
			p.erase(ptr);
			p.push_back(i);
			mp[i]++;
		}
		// Ustawia strony tak, ze pierwszy bedzie tym, ktory mozna wyrzucic
		for(int x = p.size()-2;mp[p[x]] > mp[p[x+1]]&& x >= 0;x--)std::swap(p[x],p[x+1]);

	}
	return pages_faults;
}
int main()
{
	int temp,capacity;
	std::vector<int> pages;
	std::cout<<"Capacity: ";
	std::cin>>capacity;
	std::cout<<capacity<<std::endl<<"Pages: ";
	while( std::cin>>temp )
	{
		std::cout<<temp<<" ";
		pages.emplace_back(temp);
	}
	std::cout<<std::endl<<"LRU number of pages faults: " << lru_pages_faults(pages,capacity)<<std::endl;
	std::cout<<"LFU number of pages faults: " << lfu_pages_faults(pages,capacity)<<std::endl;
	return 0;
}
