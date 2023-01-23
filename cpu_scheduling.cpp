#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>

// Struktura przechowująca informacje o procesie
struct process {
	int id;
	int arrival_time;
	int burst_time;
	int waiting_time=0;
};
// Funkcja ktora wykorzystujac fakt posortowania procesów po czasie przyjścia ustawia vector p procesów do kolejności wykonywania w LCFS.
std::vector<process> lcfs(std::vector<process> processes)
{
	std::vector<process> result;
	int proc_id;
	auto ptr = processes.begin();
	std::vector<process> stack;
	int counter=0;
	// Symulacja skonczy sie, kiedy to przejdzie prze liczbe procesow rowna ilosci procesow w processes
	for(int clock=0;counter<processes.size();clock++)
	{
		// Funckja dodająca waiting_time do procesów które oczekują (zatem wszystkie poza stack[0]
		for (int i=0;i<(int) stack.size()-1;i++)
		{
			proc_id = stack[i].id;
			// Szukanie procesu o danym id w result
			ptr = std::find_if(result.begin(),result.end(),[proc_id](const process & x) { return x.id == proc_id;}); 
			if(ptr!=result.end()) ptr->waiting_time++;
		}
		//Sprawdzenie czy niema procesu do dodania do stack oraz do results.
		for (auto &i : processes) 
		{
			if(i.arrival_time==clock)
			{
				result.emplace_back(i);
				stack.push_back(i);
			}
		}
		//
		//Jezeli stack niejest pusty i czas wykonywania procesu stack[0] jest mniejszy badz rowny 0 to usun go ze stack i do countera dodaj 1
		if(!stack.empty() && stack[stack.size()-1].burst_time<=0)
		{
			stack.pop_back();
			counter++;
		}
		if(!stack.empty())
		// Jezeli jeszcze cos zostalo w stack, zmniejsz stack[0] czas dzialania o 1.
		{
			stack[stack.size()-1].burst_time--;
		}

	}
	
	return result;
}
std::vector<process> fcfs(std::vector<process> processes)
{
	int counter=0;
	int proc_id;
	auto ptr=processes.begin();
	std::vector<process> stack;
	//int end = processes.rbegin()->arrival_time+processes.rbegin()->burst_time;
	for(int clock=0;counter<processes.size();clock++)
	{
		// Funckja dodająca waiting_time do procesów które oczekują (zatem wszystkie poza stack[0]
		for (int i=1;i<stack.size();i++)
		{
			proc_id = stack[i].id;
			// Szukanie procesu o danym id w result
			ptr = std::find_if(processes.begin(),processes.end(),[proc_id](const process & x) { return x.id == proc_id;}); 
			if(ptr!=processes.end()) ptr->waiting_time++;
		}
		// Sprawdzenie czy niema procesu do dodania do stack.
		for (auto &i : processes) 
		{
		//Sprawdzenie czy niema procesu do dodania do stack.
			if(i.arrival_time==clock)
			{
				stack.push_back(i);
			}
		}
		//Jezeli stack niejest pusty i czas wykonywania procesu stack[0] jest mniejszy badz rowny 0 to usun go ze stack i do countera dodaj 1
		if(!stack.empty())
		{
			if(stack[0].burst_time==0)
			{
				stack.erase(stack.begin());
				counter++;
			}
		// Jezeli jeszcze cos zostalo w stack, zmniejsz stack[0] czas dzialania o 1.
		stack[0].burst_time--;
		}
	}
	std::sort(processes.begin(),processes.end(),[](process a,process b){return a.arrival_time<b.arrival_time;});
	return processes;
}

// Funkcja która wyświetla procesy z wektora
void print_proc(const std::vector<process> & p)
{
	std::cout<<"ID ARRIVAL_TIME BURST_TIME WAITING_TIME"<<std::endl;
	std::cout<< p[0].id <<" "<< p[0].arrival_time <<" "<< p[0].burst_time<< " " << p[0].waiting_time << std::endl;	
	for (int i=1;i<p.size();i++)
	{
		//Proste wyliczenie czasu oczekiwania na wykonanie sie procesu
		std::cout<< p[i].id <<" "<< p[i].arrival_time <<" "<< p[i].burst_time<< " " << p[i].waiting_time << std::endl;	
	}
}
int main()
{
	int x=0;
	int completion_time=0;
	int at,bt;
	std::vector<process> p;

	// Pobieranie danych ze stumienai wyjscia.
	while(std::cin >> at >> bt)p.emplace_back(process{x++,at,bt});
	
	std::sort(p.begin(),p.end(),[](process a, process b) { return a.arrival_time < b.arrival_time; } )	
	std::cout<<"FCFS"<<std::endl;
	print_proc(fcfs(p));
	std::cout<<"LCFS"<<std::endl;
	print_proc(lcfs(p));
}
