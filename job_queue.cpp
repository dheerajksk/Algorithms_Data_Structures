#include <iostream>
#include <vector>
#include <algorithm>
<<<<<<< HEAD
=======
#include <queue>
>>>>>>> 2de3fcfd285eedd3fcb572031a64f2e788ab3082

using std::vector;
using std::cin;
using std::cout;
<<<<<<< HEAD
=======
using std::pair;
using std::make_pair;

class Worker{
  private:
    int thread_id_;
    long long finish_time_;

  public:
    Worker(){
      thread_id_ = 0;
      finish_time_ = 0;
    }

    Worker(int thread_id, long long finish_time){
      thread_id_ = thread_id;
      finish_time_ = finish_time;
    }

    int getThreadId() { return thread_id_; }
    long long getFinishTime() { return finish_time_; }

    void setThreadId( int thread_id ) { thread_id_ = thread_id; }
    void setFinishTime( long long finish_time ) { finish_time_ = finish_time; }
};
>>>>>>> 2de3fcfd285eedd3fcb572031a64f2e788ab3082

class JobQueue {
 private:
  int num_workers_;
  vector<int> jobs_;

  vector<int> assigned_workers_;
  vector<long long> start_times_;

<<<<<<< HEAD
=======
  vector< Worker >  workers_;
  int minIndex_ ;

>>>>>>> 2de3fcfd285eedd3fcb572031a64f2e788ab3082
  void WriteResponse() const {
    for (int i = 0; i < jobs_.size(); ++i) {
      cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
    }
  }

<<<<<<< HEAD
=======
  void WriteWorkers() {
    for( int i = 0; i < workers_.size(); ++i ) {
      cout << workers_[i].getThreadId() << " " ;
    }
    cout << "\n";
    for( int i = 0; i < workers_.size(); ++i ) {
      cout << workers_[i].getFinishTime() << " " ;
    }
    cout << "\n";
  }

>>>>>>> 2de3fcfd285eedd3fcb572031a64f2e788ab3082
  void ReadData() {
    int m;
    cin >> num_workers_ >> m;
    jobs_.resize(m);
    for(int i = 0; i < m; ++i)
      cin >> jobs_[i];
  }

  void AssignJobs() {
    // TODO: replace this code with a faster algorithm.
    assigned_workers_.resize(jobs_.size());
    start_times_.resize(jobs_.size());
    vector<long long> next_free_time(num_workers_, 0);
    for (int i = 0; i < jobs_.size(); ++i) {
      int duration = jobs_[i];
      int next_worker = 0;
      for (int j = 0; j < num_workers_; ++j) {
        if (next_free_time[j] < next_free_time[next_worker])
          next_worker = j;
      }
      assigned_workers_[i] = next_worker;
      start_times_[i] = next_free_time[next_worker];
      next_free_time[next_worker] += duration;
    }
  }

<<<<<<< HEAD
 public:
  void Solve() {
    ReadData();
    AssignJobs();
=======
  void SiftDown(){
    int currMinIndex = minIndex_ ;
    int l = 2*currMinIndex  + 1;

    if( l <= (workers_.size()-1) && workers_[l].getFinishTime() == workers_[minIndex_].getFinishTime() )
        if( workers_[l].getThreadId() <  workers_[minIndex_].getThreadId() ) minIndex_ = l;

    if( l <= (workers_.size()-1) && workers_[l].getFinishTime() < workers_[minIndex_].getFinishTime() )
      minIndex_ = l;

    int r = 2*currMinIndex + 2;
    if( r <= (workers_.size()-1) && workers_[r].getFinishTime() == workers_[minIndex_].getFinishTime() )
        if( workers_[r].getThreadId() <  workers_[minIndex_].getThreadId() ) minIndex_ = r;

    if( r <= (workers_.size()-1) && workers_[r].getFinishTime() < workers_[minIndex_].getFinishTime() )
      minIndex_ = r;

    if (currMinIndex != minIndex_){
      Worker temp = workers_[minIndex_];
      workers_[minIndex_].setThreadId(workers_[currMinIndex].getThreadId());
      workers_[minIndex_].setFinishTime(workers_[currMinIndex].getFinishTime());
      workers_[currMinIndex].setThreadId(temp.getThreadId());
      workers_[currMinIndex].setFinishTime(temp.getFinishTime());
      SiftDown();
  }
  }

  void AssignJobsPQ() {
    assigned_workers_.resize(jobs_.size());
    start_times_.resize(jobs_.size());
    for (int i = 0; i <  num_workers_;  i++){
      workers_.push_back(Worker(i, 0));
    }


    //WriteWorkers();
    for (int i = 0; i < jobs_.size(); ++i) {
      //cout << "jobid: " << i << "\n" ;
      //WriteWorkers();
      long long duration = jobs_[i];
      Worker next_worker = workers_.front() ;
      assigned_workers_[i] = next_worker.getThreadId();
      start_times_[i] = next_worker.getFinishTime();
      workers_[0].setFinishTime(start_times_[i] + duration);
      minIndex_ = 0;
      SiftDown();
    }
  }

 public:
  void Solve() {
    ReadData();
    AssignJobsPQ();
>>>>>>> 2de3fcfd285eedd3fcb572031a64f2e788ab3082
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  JobQueue job_queue;
  job_queue.Solve();
  return 0;
}
