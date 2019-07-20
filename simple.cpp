#include <chrono>
#include <cmath>
#include <hpx/hpx_main.hpp>
#include <hpx/include/compute.hpp>
#include <hpx/parallel/algorithm.hpp>
#include <hpx/parallel/execution_policy.hpp>
#include <iostream>
#include <string_view>
#include <algorithm>

using Clock = std::chrono::high_resolution_clock;

// Just a function that takes some time to compute
double acumula(unsigned long long num_sampes) {
  double saida = 0;
  for (unsigned long long i = 0; i < num_sampes; ++i) {
    saida += std::sin(std::cos(i));
  }
  return saida;
}


void print_elapsed_time(std::string_view label, Clock::time_point toc, Clock::time_point tic) {
  auto duration =
      std::chrono::duration_cast<std::chrono::milliseconds>(toc - tic);
  std::cout << label << " Elapsed time: " << duration.count() / 1000.0
            << std::endl;
}


int main(int argc, char *argv[]) {
  unsigned long long N = 10000000;
  std::vector<unsigned long long> Ns{N, N, N, N};

  // xxxxxxxxxx Serial Version xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  auto tic = Clock::now();
  for(auto n : Ns) {
    // Volatile makes sure the compiler does not optimize this away in release
    double volatile saida = acumula(n);
  }
  auto toc = Clock::now();
  print_elapsed_time("Serial", toc, tic);
  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  // xxxxxxxxxx Parallel version xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  auto tic2 = Clock::now();
  hpx::parallel::for_each(hpx::parallel::execution::par, Ns.begin(), Ns.end(), acumula);
  auto toc2 = Clock::now();
  print_elapsed_time("Parallel", toc2, tic2);
  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  // 8 Threads in my computer
  auto host_targets = hpx::compute::host::get_local_targets();
  std::cout << host_targets.size() << std::endl;

  return 0;
}
