//
// Created by milos on 20/02/2024.
//

#ifndef ND_KNN_DISTANCEMATRIXBUILDER_H
#define ND_KNN_DISTANCEMATRIXBUILDER_H


#include "DistanceMatrix.h"
#include "../DijkstraSearch.h"
#include "AdaptiveGtreeNode.h"

class DistanceMatrixBuilder {
public:
    void static fillColumn(Graph &graph, DistanceMatrix &matrix, NodeID sourceNodeID, int sourceIdx,
                           const std::vector<NodeID> &targetsVec) {
        BinaryMinHeap<EdgeWeight, NodeID> pqueue_local = BinaryMinHeap<EdgeWeight, NodeID>();
        DijkstraSearch dijkstra;
        std::unordered_set<NodeID> targetsUset(targetsVec.begin(), targetsVec.end());
        std::unordered_map<NodeID, EdgeWeight> siblingBorderDistances;
//        std::cout << "column not assigned, borders size: " << targetsVec.size() << std::endl;
        dijkstra.findSSMTDistances(graph, sourceNodeID, targetsUset, siblingBorderDistances, &pqueue_local);

        for (std::size_t j = 0; j < targetsVec.size(); ++j) {
            auto weight = siblingBorderDistances[targetsVec[j]];
//            std::cout << "setting weight: " << j << "," << sourceIdx << " " << weight << std::endl;
            matrix.set(j, sourceIdx, siblingBorderDistances[targetsVec[j]]);
        }
    }

    void static fillRow(Graph &graph, AdaptiveGtreeNode& node, NodeID sourceNodeID, int sourceIdx,
                        const std::vector<NodeID> &targetsVec) {
        DistanceMatrix& matrix = node.distanceMatrix;
        BinaryMinHeap<EdgeWeight, NodeID> pqueue_local = BinaryMinHeap<EdgeWeight, NodeID>();
        DijkstraSearch dijkstra;
        std::unordered_set<NodeID> targetsUset(targetsVec.begin(), targetsVec.end());
        std::unordered_map<NodeID, EdgeWeight> siblingBorderDistances;
//        std::cout << "row not assigned, borders size: " << targetsVec.size() << std::endl;
        dijkstra.findSSMTDistances(graph, sourceNodeID, targetsUset, siblingBorderDistances, &pqueue_local);

        for (std::size_t j = 0; j < targetsVec.size(); ++j) {
            auto weight = siblingBorderDistances[targetsVec[j]];
            int targetBorderIdx = node.getBorderIdxInChildBorderVec(j);
//            std::cout << "setting weight: " << j << "," << sourceIdx << " " << weight << std::endl;
            matrix.set(sourceIdx, targetBorderIdx, siblingBorderDistances[targetsVec[j]]);
        }
    }
};


#endif //ND_KNN_DISTANCEMATRIXBUILDER_H