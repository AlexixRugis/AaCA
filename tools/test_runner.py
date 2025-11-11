import subprocess
from typing import List, Tuple
import matplotlib.pyplot as plt
import math
from pathlib import Path

EXE_PATH_TESTS = Path(r"/home/alexix/Repos/AaCA/build/bin/GraphComponents_tests")
EXE_PATH_COMP = Path(r"/home/alexix/Repos/AaCA/build/bin/GraphComponents_one_comp")
N_VALUES = list(range(1, 1001 + 1, 10))

def run_program_raw_data(exe_path: str, input_data: Tuple):
    exe = Path(exe_path).resolve()
    if not exe.exists():
        raise FileNotFoundError(f"Executable not found: {exe}")

    work_dir = exe.parent

    input_file = work_dir / "input.txt"
    with open(input_file, "w") as f:
        for elem in input_data:
            f.write(f"{elem} ")
            
    result = subprocess.run([str(exe)], cwd=work_dir, capture_output=True, text=True)
    if result.returncode != 0:
        raise RuntimeError(
            f"Program exited with code {result.returncode}\n"
            f"stderr:\n{result.stderr}"
        )
        
    def read_output(filename: str) -> float:
        path = work_dir / filename
        if not path.exists():
            raise FileNotFoundError(f"Output file not found: {path}")
        with open(path, "r") as f:
            return f.readlines()
        
    naive = read_output("output_naive.txt")
    ram = read_output("output_ram.txt")

    return naive, ram

def run_test_program(exe_path: str, n: int, m: int):    
    naive, ram = run_program_raw_data(exe_path, (n, m))
    return float(naive[0].strip()), float(ram[0].strip())

def run_comp_program(exe_path: str, n: int):
    naive, ram = run_program_raw_data(exe_path, (n, ))
    return int(ram[0].strip())

def run_experiment(name: str, m_func) -> Tuple[List[int], List[float], List[float]]:
    n_vals, t_naive, t_ram = [], [], []

    for n in N_VALUES:
        m = int(m_func(n))
        try:
            naive, ram = run_test_program(EXE_PATH_TESTS, n, m)
            n_vals.append(n)
            t_naive.append(naive)
            t_ram.append(ram)
            print(f"{name}: n={n}, m={m}, T_A={naive:.6f}, T_B={ram:.6f}")
        except Exception as e:
            print(f"Ошибка при n={n}, m={m}: {e}")

    return n_vals, t_naive, t_ram

def run_comp_experiment(name: str) -> Tuple[List[int], List[int]]:
    n_vals, n_edges = [], []
    
    for n in N_VALUES:
        try:
            edges_count = run_comp_program(EXE_PATH_COMP, n)
            n_vals.append(n)
            n_edges.append(edges_count)
            
            print(f"{name}: n={n}, m={edges_count}")
        except Exception as e:
            print(f"Ошибка при n={n}: {e}")
    
    return n_vals, n_edges

def plot_results(n_vals, n_name, graphs, title, save_dir="plots"):
    plt.figure()
    
    for key, value in graphs.items():
        plt.plot(n_vals, value, label=key, linewidth=1.5)
    
    plt.xlabel("n")
    plt.ylabel(n_name)
    plt.title(title)
    plt.legend()
    plt.grid(True)
    plt.tight_layout()
    
    safe_name = title.replace(":", "").replace(" ", "_").replace("/", "_")
    file_path = Path(save_dir) / f"{safe_name}.png"
    plt.savefig(file_path, dpi=200)
    plt.close()
    
def experiment_1():
    n_vals, t_naive, t_ram = run_experiment("e1", lambda n: round(n * n / 10))
    plot_results(n_vals, "Время (T)", {'T_A (naive)': t_naive, 'T_B (ram)': t_ram}, "e1: m = n2 / 10")


def experiment_2():
    n_vals, t_naive, t_ram = run_experiment("e2", lambda n: n - 1)
    plot_results(n_vals, "Время (T)", {'T_A (naive)': t_naive, 'T_B (ram)': t_ram}, "e2: m = n - 1")


def experiment_3():
    n_vals, t_naive, t_ram = run_experiment("e3", lambda n: round(math.log2(n)))
    plot_results(n_vals, "Время (T)", {'T_A (naive)': t_naive, 'T_B (ram)': t_ram}, "e3: m = log2(n)")
    
def experiment_4():
    n_vals, n_edges = run_comp_experiment("one_comp")
    plot_results(n_vals, "Кол-во вершин (N)", {'N_E (edges)': n_edges,}, "e4: one comp")

def main():
    #experiment_1()
    #experiment_2()
    #experiment_3()
    experiment_4()
    
if __name__ == '__main__':
    main()