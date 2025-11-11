# 🍽️ Philosophers - 42 School Project

**Philosophers** (Philo) is a C project from **42 School** based on the classic **Dining Philosophers Problem**, a concurrency problem that teaches synchronization, deadlock avoidance, and process/thread management.

---

## 🎯 Project Goals

- Simulate **philosophers sitting at a table**, alternating between **thinking**, **eating**, and **sleeping**.  
- Each philosopher needs **two forks** (represented by mutexes or semaphores) to eat.  
- Ensure that the program avoids **deadlocks** and **race conditions**.  
- Handle timing correctly so philosophers eat, sleep, and think for the specified durations.  
- Bonus: Implement a **process-based version** instead of threads.

---

## 📚 Features

- Philosophers are modeled as **threads or processes** depending on the implementation.  
- Each philosopher follows the cycle:  
  1. Think  
  2. Pick up forks (mutex/semaphore)  
  3. Eat  
  4. Put down forks  
  5. Sleep  
- Accurate **timing** to avoid philosophers starving.  
- Safe and synchronized printing of philosopher states.  
- Proper termination when a philosopher dies or when the simulation ends.  
- Bonus: **Process-based implementation** using **semaphores** and `fork()`.

---

## ⚙️ Usage

### Compile the program:

```bash
make
make fclean
make clean
make re
make bonus
