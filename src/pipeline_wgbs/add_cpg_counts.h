//
// Created by nloyfer on 9/14/18.
//

#ifndef FAST_PAT_PATTER_H
#define FAST_PAT_PATTER_H

#include <iostream>
#include <ctime>
//#include <string>
#include <vector>
#include <algorithm>    // std::sort
#include <fstream>
#include <regex>
#include <unordered_map>
#include <sstream>      // std::stringstream


#define MAX_PAT_LEN 300

struct reads_stats {
    int nr_pairs = 0;
    int nr_empty = 0;
    int nr_invalid = 0;
    int nr_short = 0;
};

class patter {
public:
    std::string ref_path;
    std::string chrom_sz_path;
    std::string chr;
    std::unordered_map<int, int> dict;
    std::string genome_ref;
    reads_stats readsStats;
    std::string TAGNAMETYPE = "YI:Z:";
    int min_cpg = 0;
    int line_i = 0;
    bool is_paired_end = false;
    bool first_line(std::string &line);

    struct MethylData {
        int countMethyl; int countUnmethyl;
        int originalIndex;
    };


    patter(std::string refpath, std::string cspath, int min_len): ref_path(refpath), chrom_sz_path(cspath), min_cpg(min_len) {}

    void load_genome_ref();
    int find_cpg_inds_offset();
    std::vector<long> fasta_index();


    void print_stats_msg();
    void print_progress();
    int locus2CpGIndex(int locus);
    std::string clean_seq(std::string seq, std::string CIGAR);
    std::vector<std::string> samLineToPatVec(std::vector<std::string> tokens);
    std::vector<std::string> samLineToPatVec2(std::vector<std::string> tokens);
    void handlyMethylCountSamLine(std::string line);
    std::string samLineToSamLineWithMethCounts(std::vector<std::string> tokens, std::string originalLine);
    MethylData samLineToMethCounts(std::vector <std::string> tokens, std::string originalLine);
    void action_sam(std::string samFilePath);
    void handle_action_sam_line(std::string line_str, bool first_in_pair);
    std::string samLineMethyldataMakeString(std::string originalLine, patter::MethylData md);
    void merge_and_print(std::vector<std::string> l1, std::vector<std::string> l2);
    void proc_sam_in_stream(std::istream& in);
    patter::MethylData merge_and_count_methyl_data(std::vector <std::string> l1, std::vector <std::string> l2);
    void proc2lines(std::vector<std::string> tokens1, std::vector<std::string> tokens2);
    void procPairAddMethylData(std::vector<std::string> tokens1, std::vector<std::string> tokens2,
                               std::string line1, std::string line2);
    void action();
    void addMethylCountToSam(std::string samFilePath);

    void initialize_patter(std::string &line_str);

    void proc_pair_sam_lines(std::string &line1,
                             std::string &line2);
};

std::vector<std::string> line2tokens(std::string &line);
void print_vec(std::vector<std::string> &vec);

#endif //FAST_PAT_PATTER_H