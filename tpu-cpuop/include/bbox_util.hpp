#ifndef BMCPU_UTIL_BBOX_UTIL_H_
#define BMCPU_UTIL_BBOX_UTIL_H_

#include <stdint.h>
#include <cmath>  // for std::fabs and std::signbit
#include <map>
#include <string>
#include <utility>
#include <vector>

#include <float.h>

#include "NormalizedBBox.h"

using std::fstream;
using std::ios;
using std::iterator;
using std::make_pair;
using std::map;
using std::ostringstream;
using std::pair;
using std::set;
using std::string;
using std::stringstream;
using std::vector;


namespace bmcpu {

typedef map<int, vector<NormalizedBBox> > LabelBBox;

enum PriorBoxParameter_CodeType {
	  PriorBoxParameter_CodeType_CORNER = 1,
	    PriorBoxParameter_CodeType_CENTER_SIZE = 2,
	      PriorBoxParameter_CodeType_CORNER_SIZE = 3
};

typedef PriorBoxParameter_CodeType CodeType;



typedef map<int, vector<NormalizedBBox> > LabelBBox;

// Function used to sort NormalizedBBox, stored in STL container (e.g. vector),
// in ascend order based on the score value.
bool SortBBoxAscend(const NormalizedBBox& bbox1, const NormalizedBBox& bbox2);

// Function used to sort NormalizedBBox, stored in STL container (e.g. vector),
// in descend order based on the score value.
bool SortBBoxDescend(const NormalizedBBox& bbox1, const NormalizedBBox& bbox2);

// Function sued to sort pair<float, T>, stored in STL container (e.g. vector)
// in descend order based on the score (first) value.
template <typename T>
bool SortScorePairAscend(const pair<float, T>& pair1,
                         const pair<float, T>& pair2);

// Function sued to sort pair<float, T>, stored in STL container (e.g. vector)
// in descend order based on the score (first) value.
template <typename T>
bool SortScorePairDescend(const pair<float, T>& pair1,
                          const pair<float, T>& pair2);
template <class T>
void insert_sort(T begin, T end);

// Generate unit bbox [0, 0, 1, 1]
NormalizedBBox UnitBBox();

// Check if a bbox is cross boundary or not.
bool IsCrossBoundaryBBox(const NormalizedBBox& bbox);

// Compute the intersection between two bboxes.
void IntersectBBox(const NormalizedBBox& bbox1, const NormalizedBBox& bbox2,
                   NormalizedBBox* intersect_bbox);

// Compute bbox size.
float BBoxSize(const NormalizedBBox& bbox, const bool normalized = true);

template <typename Dtype>
Dtype BBoxSize(const Dtype* bbox, const bool normalized = true);

// Clip the NormalizedBBox such that the range for each corner is [0, 1].
void ClipBBox(const NormalizedBBox& bbox, NormalizedBBox* clip_bbox);

// Clip the bbox such that the bbox is within [0, 0; width, height].
void ClipBBox(const NormalizedBBox& bbox, const float height, const float width,
              NormalizedBBox* clip_bbox);

// Scale the NormalizedBBox w.r.t. height and width.
void ScaleBBox(const NormalizedBBox& bbox, const int height, const int width,
               NormalizedBBox* scale_bbox);

void LocateBBox(const NormalizedBBox& src_bbox, const NormalizedBBox& bbox,
                NormalizedBBox* loc_bbox);

// Project bbox onto the coordinate system defined by src_bbox.
bool ProjectBBox(const NormalizedBBox& src_bbox, const NormalizedBBox& bbox,
                 NormalizedBBox* proj_bbox);


// Compute the jaccard (intersection over union IoU) overlap between two bboxes.
float JaccardOverlap(const NormalizedBBox& bbox1, const NormalizedBBox& bbox2,
                     const bool normalized = true);

template <typename Dtype>
Dtype JaccardOverlap(const Dtype* bbox1, const Dtype* bbox2);

// Compute the coverage of bbox1 by bbox2.
float BBoxCoverage(const NormalizedBBox& bbox1, const NormalizedBBox& bbox2);

// Encode a bbox according to a prior bbox.
void EncodeBBox(const NormalizedBBox& prior_bbox,
    const vector<float>& prior_variance, const CodeType code_type,
    const bool encode_variance_in_target, const NormalizedBBox& bbox,
    NormalizedBBox* encode_bbox);


// Decode a bbox according to a prior bbox.
void DecodeBBox(const NormalizedBBox& prior_bbox,
    const vector<float>& prior_variance, const CodeType code_type,
    const bool variance_encoded_in_target, const bool clip_bbox,
    const NormalizedBBox& bbox, NormalizedBBox* decode_bbox);

// Decode a set of bboxes according to a set of prior bboxes.
void DecodeBBoxes(const vector<NormalizedBBox>& prior_bboxes,
    const vector<vector<float> >& prior_variances,
    const CodeType code_type, const bool variance_encoded_in_target,
    const bool clip_bbox, const vector<NormalizedBBox>& bboxes,
    vector<NormalizedBBox>* decode_bboxes);

// Decode all bboxes in a batch.
void DecodeBBoxesAll(const vector<LabelBBox>& all_loc_pred,
    const vector<NormalizedBBox>& prior_bboxes,
    const vector<vector<float> >& prior_variances,
    const int num, const bool share_location,
    const int num_loc_classes, const int background_label_id,
    const CodeType code_type, const bool variance_encoded_in_target,
    const bool clip, vector<LabelBBox>* all_decode_bboxes);

void DecodeBBoxesAll(const vector<NormalizedBBox>& all_loc_pred,
    const vector<NormalizedBBox>& prior_bboxes,
    const vector<vector<float> >& prior_variances,
    const int num, const bool share_location,
    const int num_loc_classes, const int background_label_id,
    const CodeType code_type, const bool variance_encoded_in_target,
    const bool clip, vector<NormalizedBBox>* all_decode_bboxes);

// Count the number of matches from the match indices.
int CountNumMatches(const vector<map<int, vector<int> > >& all_match_indices,
                    const int num);

// Retrieve bounding box ground truth from gt_data.
//    gt_data: 1 x 1 x num_gt x 7 blob.
//    num_gt: the number of ground truth.
//    background_label_id: the label for background class which is used to do
//      santity check so that no ground truth contains it.
//    all_gt_bboxes: stores ground truth for each image. Label of each bbox is
//      stored in NormalizedBBox.
template <typename Dtype>
void GetGroundTruth(const Dtype* gt_data, const int num_gt,
      const int background_label_id, const bool use_difficult_gt,
      map<int, vector<NormalizedBBox> >* all_gt_bboxes);
// Store ground truth bboxes of same label in a group.
template <typename Dtype>
void GetGroundTruth(const Dtype* gt_data, const int num_gt,
      const int background_label_id, const bool use_difficult_gt,
      map<int, LabelBBox>* all_gt_bboxes);

// Get location predictions from loc_data.
//    loc_data: num x num_preds_per_class * num_loc_classes * 4 blob.
//    num: the number of images.
//    num_preds_per_class: number of predictions per class.
//    num_loc_classes: number of location classes. It is 1 if share_location is
//      true; and is equal to number of classes needed to predict otherwise.
//    share_location: if true, all classes share the same location prediction.
//    loc_preds: stores the location prediction, where each item contains
//      location prediction for an image.
template <typename Dtype>
void GetLocPredictions(const Dtype* loc_data, const int num,
      const int num_preds_per_class, const int num_loc_classes,
      const bool share_location, vector<LabelBBox>* loc_preds);

template <typename Dtype>
void GetLocPredictions(const Dtype* loc_data, const int num,
      const int num_preds_per_class, const int num_loc_classes,
      const bool share_location, vector<NormalizedBBox>* loc_preds);

// Get confidence predictions from conf_data.
//    conf_data: num x num_preds_per_class * num_classes blob.
//    num: the number of images.
//    num_preds_per_class: number of predictions per class.
//    num_classes: number of classes.
//    conf_preds: stores the confidence prediction, where each item contains
//      confidence prediction for an image.
template <typename Dtype>
void GetConfidenceScores(const Dtype* conf_data, const int num,
      const int num_preds_per_class, const int num_classes,
      vector<map<int, vector<float> > >* conf_scores);

// Get confidence predictions from conf_data.
//    conf_data: num x num_preds_per_class * num_classes blob.
//    num: the number of images.
//    num_preds_per_class: number of predictions per class.
//    num_classes: number of classes.
//    class_major: if true, data layout is
//      num x num_classes x num_preds_per_class; otherwise, data layerout is
//      num x num_preds_per_class * num_classes.
//    conf_preds: stores the confidence prediction, where each item contains
//      confidence prediction for an image.
template <typename Dtype>
void GetConfidenceScores(const Dtype* conf_data, const int num,
      const int num_preds_per_class, const int num_classes,
      const bool class_major, vector<map<int, vector<float> > >* conf_scores);




// Get prior bounding boxes from prior_data.
//    prior_data: 1 x 2 x num_priors * 4 x 1 blob.
//    num_priors: number of priors.
//    prior_bboxes: stores all the prior bboxes in the format of NormalizedBBox.
//    prior_variances: stores all the variances needed by prior bboxes.
template <typename Dtype>
void GetPriorBBoxes(const Dtype* prior_data, const int num_priors,
      vector<NormalizedBBox>* prior_bboxes,
      vector<vector<float> >* prior_variances);

// Get detection results from det_data.
//    det_data: 1 x 1 x num_det x 7 blob.
//    num_det: the number of detections.
//    background_label_id: the label for background class which is used to do
//      santity check so that no detection contains it.
//    all_detections: stores detection results for each class from each image.
template <typename Dtype>
void GetDetectionResults(const Dtype* det_data, const int num_det,
      const int background_label_id,
      map<int, LabelBBox>* all_detections);

// Get top_k scores with corresponding indices.
//    scores: a set of scores.
//    indices: a set of corresponding indices.
//    top_k: if -1, keep all; otherwise, keep at most top_k.
//    score_index_vec: store the sorted (score, index) pair.
void GetTopKScoreIndex(const vector<float>& scores, const vector<int>& indices,
      const int top_k, vector<pair<float, int> >* score_index_vec);

// Get max scores with corresponding indices.
//    scores: a set of scores.
//    threshold: only consider scores higher than the threshold.
//    top_k: if -1, keep all; otherwise, keep at most top_k.
//    score_index_vec: store the sorted (score, index) pair.
void GetMaxScoreIndex(const vector<float>& scores, const float threshold,
      const int top_k, vector<pair<float, int> >* score_index_vec);

// Get max scores with corresponding indices.
//    scores: an array of scores.
//    num: number of total scores in the array.
//    threshold: only consider scores higher than the threshold.
//    top_k: if -1, keep all; otherwise, keep at most top_k.
//    score_index_vec: store the sorted (score, index) pair.
template <typename Dtype>
void GetMaxScoreIndex(const Dtype* scores, const int num, const float threshold,
      const int top_k, vector<pair<Dtype, int> >* score_index_vec);

// Get max scores with corresponding indices.
//    scores: a set of scores.
//    threshold: only consider scores higher than the threshold.
//    top_k: if -1, keep all; otherwise, keep at most top_k.
//    score_index_vec: store the sorted (score, index) pair.
void GetMaxScoreIndex(const vector<float>& scores, const float threshold,
      const int top_k, vector<pair<float, int> >* score_index_vec);

// Do non maximum suppression given bboxes and scores.
//    bboxes: a set of bounding boxes.
//    scores: a set of corresponding confidences.
//    threshold: the threshold used in non maximum suppression.
//    top_k: if not -1, keep at most top_k picked indices.
//    reuse_overlaps: if true, use and update overlaps; otherwise, always
//      compute overlap.
//    overlaps: a temp place to optionally store the overlaps between pairs of
//      bboxes if reuse_overlaps is true.
//    indices: the kept indices of bboxes after nms.
void ApplyNMS(const vector<NormalizedBBox>& bboxes, const vector<float>& scores,
      const float threshold, const int top_k, const bool reuse_overlaps,
      map<int, map<int, float> >* overlaps, vector<int>* indices);

void ApplyNMS(const vector<NormalizedBBox>& bboxes, const vector<float>& scores,
      const float threshold, const int top_k, vector<int>* indices);

void ApplyNMS(const bool* overlapped, const int num, vector<int>* indices);

// Do non maximum suppression given bboxes and scores.
// Inspired by Piotr Dollar's NMS implementation in EdgeBox.
// https://goo.gl/jV3JYS
//    bboxes: a set of bounding boxes.
//    scores: a set of corresponding confidences.
//    score_threshold: a threshold used to filter detection results.
//    nms_threshold: a threshold used in non maximum suppression.
//    eta: adaptation rate for nms threshold (see Piotr's paper).
//    top_k: if not -1, keep at most top_k picked indices.
//    indices: the kept indices of bboxes after nms.
void ApplyNMSFast(const vector<NormalizedBBox>& bboxes,
      const vector<float>& scores, const float score_threshold,
      const float nms_threshold, const float eta, const int top_k,
      vector<int>* indices);

// Do non maximum suppression based on raw bboxes and scores data.
// Inspired by Piotr Dollar's NMS implementation in EdgeBox.
// https://goo.gl/jV3JYS
//    bboxes: an array of bounding boxes.
//    scores: an array of corresponding confidences.
//    num: number of total boxes/confidences in the array.
//    score_threshold: a threshold used to filter detection results.
//    nms_threshold: a threshold used in non maximum suppression.
//    eta: adaptation rate for nms threshold (see Piotr's paper).
//    top_k: if not -1, keep at most top_k picked indices.
//    indices: the kept indices of bboxes after nms.
template <typename Dtype>
void ApplyNMSFast(const Dtype* bboxes, const Dtype* scores, const int num,
      const float score_threshold, const float nms_threshold,
      const float eta, const int top_k, vector<int>* indices);

// Compute cumsum of a set of pairs.
void CumSum(const vector<pair<float, int> >& pairs, vector<int>* cumsum);

// Compute average precision given true positive and false positive vectors.
//    tp: contains pairs of scores and true positive.
//    num_pos: number of positives.
//    fp: contains pairs of scores and false positive.
//    ap_version: different ways of computing Average Precision.
//      Check https://sanchom.wordpress.com/tag/average-precision/ for details.
//      11point: the 11-point interpolated average precision. Used in VOC2007.
//      MaxIntegral: maximally interpolated AP. Used in VOC2012/ILSVRC.
//      Integral: the natural integral of the precision-recall curve.
//    prec: stores the computed precisions.
//    rec: stores the computed recalls.
//    ap: the computed Average Precision.
void ComputeAP(const vector<pair<float, int> >& tp, const int num_pos,
               const vector<pair<float, int> >& fp, const string ap_version,
               vector<float>* prec, vector<float>* rec, float* ap);

}  // namespace bmnetc

#endif  // bmnetc_UTIL_BBOX_UTIL_H_
